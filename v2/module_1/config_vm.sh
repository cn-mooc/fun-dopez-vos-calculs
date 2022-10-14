#!/bin/sh
set -e
set -o noglob

# --- helper functions for logs ---
info()
{
    echo '[INFO] ' "$@"
}
warn()
{
    echo '[WARN] ' "$@" >&2
}
fatal()
{
    echo '[ERROR] ' "$@" >&2
    exit 1
}

# === VARIABLES ===
export FUN_GITDIR=fun-dopez-vos-calculs.git

# === APT Stuff ===
apt_stuff(){
    export DEBIAN_FRONTEND=noninteractive
    APT_OPT=""
    DIST_CODENAME=$(lsb_release -cs)
    if [ $(lsb_release -is) = "Debian" ]; then
        apt-get install -y software-properties-common dirmngr
            if [[ $DIST_CODENAME == "stretch" || $DIST_CODENAME == "buster" ]]; then
            apt-add-repository "deb http://deb.debian.org/debian ${DIST_CODENAME}-backports main";
        fi
        APT_OPT="-t ${DIST_CODENAME}-backports --allow-unauthenticated"
        apt-get -y --allow-unauthenticated dist-upgrade
    elif [ $DIST_CODENAME != "focal" ]; then
        apt-add-repository -y ppa:ansible/ansible
    fi
    apt-get update
    apt-get install $APT_OPT -y ansible
}

# === ANSIBLE Stuff ===
# --- if we are inside the git repo directory
ansible_stuff(){
    if [ -f ansible.yml ]; then
        git pull
    else
        if [ -d "$FUN_GITDIR" ]; then
            fatal "Please remove current [$FUN_GITDIR] first..."
            return 1
        fi
        git clone https://github.com/cn-mooc/$FUN_GITDIR && \
        cd fun-dopez-vos-calculs/v2/module_1 || fatal "Not in a repo directory"
    fi
    # --- Remove the comment below if you want to run debug mode
    #export ANSIBLE_DEBUG=true
    export ANSIBLE_VERBOSITY=2
    ansible-playbook -c local -i 127.0.0.1, -b -e 'ansible_python_interpreter=/usr/bin/python3' ansible.yml
}

# === MAIN ===
{
    apt_stuff
    ansible_stuff
}