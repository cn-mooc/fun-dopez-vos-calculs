#!/bin/sh
set -e
set -o noglob

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
ansible-playbook -c local -i 127.0.0.1, -b -e 'ansible_python_interpreter=/usr/bin/python3' ansible.yml
