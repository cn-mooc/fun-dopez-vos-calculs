#!/bin/bash
# Copyright - Centrale Nantes
# Version 1.0 @ Fri Oct 14 19:24:50 UTC 2022
# source: https://slurm.schedmd.com/overview.html
#
set -x

FILE_CODE=slurm
FILE_GIT=https://github.com/SchedMD/slurm
WORK_DIR=`mktemp -d`
SLURM_FILE="slurm-local.conf"

fatal(){
  echo '[ERROR] ***' "$@" >&2
  exit 1
}

# --- apt installation
[ -d ${WORK_DIR ] && {
  cp -a $SLURM_FILE ${WORK_DIR}
  cd ${WORK_DIR} && {
    apt update -y
    apt install -y slurmd slurmctld || fatal 'installation non reussie'
  }
} || fatal 'probleme avec mktemp'

# --- if install succeed, remove temp directory
hash slurmd 2>/dev/null || fatal 'les paquets slurm mal installes'
export FILE_VER=${1:-$(slurmd -V | awk '{print $2}')}

cd /etc/slurm || cd /etc/slurm-llnl || exit 1 
# --- backup existing slurm configuration
cp -a slurm.conf slurm-bak-`date +%s`_conf
# --- copy the new slurm configuration based to the local specs
cat ${WORK_DIR}/slurm-local.conf 2>/dev/null > slurm.conf
cat<<EOF>>slurm.conf
$(slurmd -C | grep ^NodeName 2>/dev/null)
PartitionName=LocalQ Nodes=ALL Default=YES MaxTime=INFINITE State=UP
EOF

# --- restart slurm daemons
systemctl start slurmctld
systemctl start slurmd

# --- test installation and queue info
sinfo 2>/dev/null | grep -q ^LocalQ || fatal 'probleme avec la gestion de queue slurm, regardez le fichier de configuration /etc/slurm/slurm.conf'

echo "--- slurm version $FILE_VER installed. ---"
rm -rf $WORK_DIR 2>/dev/null
exit 0
