USER=`whoami`
if [ $USER = "root" ]
        then
        echo "Running as ROOT"
else
        echo "***********YOU ARE NOT ROOT************" 
        exit 0
fi

if [ -d "/home/Music" ]
then 
    echo "/home/Music exists!"
else 
    echo "Creating ~/Music Directory"
    mkdir /home/Music
fi

if [ -d `pwd`/../assets ]
then
    cp `pwd`/../assets/*.ttf /usr/share/fonts
    echo "Copied fonts from ../assets/ to /usr/share/fonts directory"
fi

if [ -d `pwd`/../SongLibrary ]
then
    cp `pwd`/../SongLibrary/*.mp3 /home/Music
    echo "Copied Music from ../SongLibrary to ~/Music directory"
fi

#echo "You are running on the pi, we will set up Auto Launch"
cd ..


ARCHITECTURE=`uname -m`
if [ ${ARCHITECTURE} = "armv7l" ]
then
    echo "You are running on armv7l. Assuming you are a Raspberry Pi"

    #Sets up Fastboot
    apt-get install systemd
    FASTBOOT=`cat /boot/cmdline.txt`
    SYSTEMSET=`echo $FASTBOOT | grep -o "systemd"`
    if [ -z $SYSTEMSET ]
    then
        sudo sh -c 'FASTBOOT=`cat /boot/cmdline.txt`; echo -n "$FASTBOOT init=/bin/systemd" > /boot/cmdline.txt'
    fi 
    
    #Sets up Autoboot
    FILECONTENTS=`grep -Eo "BackupCamera" /etc/rc.local`
    echo filecontents = ${FILECONTENTS[0]}
    if [ -z "${FILECONTENTS[0]}" ]
    then
            echo "Setting up AutoLaunch"
            sed -i '$ d' /etc/rc.local
            sudo sh -c 'CAMERAPATH=`pwd`; echo "$CAMERAPATH/BackupCamera" >> /etc/rc.local'
            echo "exit 0" >> /etc/rc.local
    else
            echo "Autolaunch already set up!"
    fi

else
    echo "Not on armv7l. Assuming you are not a Raspberry Pi"
fi


