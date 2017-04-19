#!/bin/bash


apt-get update
apt-get -y upgrade
apt-get -y install build-essential gcc-multilib execstack gdb python-pip ipython python-virtualenv git \
	libtool automake python-dev g++ gcc texinfo curl wget autoconf python subversion unzip \
	virtualenvwrapper sudo

pip install appdirs

echo 0 | tee /proc/sys/kernel/randomize_va_space
echo core | tee /proc/sys/kernel/core_pattern

