#!/bin/bash

/opt/chroots/debian_jessie_x32/mount_jenkins.sh

echo "Build Hosts Package"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "mkdir -p /root/jenkins/workspace/libhosts/build"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "rm -f /root/jenkins/workspace/libhosts/build/piga-libhosts-dev-*"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/libhosts/build && cmake .. -DHOSTS_VERSION_PATCH="\""$(cat /var/lib/jenkins/jobs/libhosts/nextBuildNumber)"\"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/libhosts/build && make package"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/libhosts/build && make install"

echo "Add the hosts package to the repository"
PIGA_DEB="$(ls /var/lib/jenkins/workspace/libhosts/build/*deb)"
echo "DEBFILE: $PIGA_DEB"
cd /media/maximaximal.com/www/repos/apt/debian && sudo reprepro includedeb jessie "$PIGA_DEB"

echo "Build Arduino Host"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "mkdir -p /root/jenkins/workspace/libhosts/arduino/build"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "rm -f /root/jenkins/workspace/libhosts/arduino/piga-libhosts-arduino*"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/libhosts/arduino/build && cmake .. -DARDUINO_HOST_VERSION_PATCH="\""$(cat /var/lib/jenkins/jobs/libhosts/nextBuildNumber)"\"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/libhosts/arduino/build && make package"
sudo chroot /opt/chroots/debian_jessie_x32 /bin/bash -c "cd /root/jenkins/workspace/libhosts/arduino/build && make install"

echo "Add the arduino host package to the repository"
PIGA_DEB="$(ls /var/lib/jenkins/workspace/libhosts/arduino/build/*deb)"
echo "DEBFILE: $PIGA_DEB"
cd /media/maximaximal.com/www/repos/apt/debian && sudo reprepro includedeb jessie "$PIGA_DEB"


/opt/chroots/debian_jessie_x32/umount_jenkins.sh
