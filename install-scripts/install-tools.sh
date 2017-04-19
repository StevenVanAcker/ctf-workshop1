#!/bin/bash -e

cd $HOME
if [ ! -e ctf-tools ];
then
	git clone https://github.com/zardus/ctf-tools.git
        cd ctf-tools
	./bin/manage-tools -s setup
        echo "workon ctftools" >> $HOME/.bashrc
fi

for i in pwntools afl checksec;
do
    bash -ic "manage-tools -s uninstall $i; manage-tools -s install $i"
    echo
done

if [ ! -e "$HOME/ctf-tools/afl/afl-bin" ];
then
	cd $HOME/ctf-tools/afl/
	mkdir -p afl-bin
	cd afl-bin
	for i in {as,cmin,gcc,gotcpu,plot,qemu-trace,showmap,tmin,whatsup}; do ln -s ../afl/afl-$i $i; done
	grep -q AFL_PATH $HOME/.bashrc || echo "export AFL_PATH=\"$HOME/ctf-tools/afl/afl-bin\"" >> $HOME/.bashrc
fi
