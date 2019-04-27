#/usr/bin/env bash
backupCam="/home/pi/Documents/SolarCar/BackupCamera/BackupCamera 0 0 800 480 800 600 &"
eval $backupCam
pid=$!
sleep 2
sudo kill $pid

eval $backupCam
pid=$!
sleep 2
sudo kill $pid
eval $backupCam

pid=$!
sleep 2
sudo kill $pid
eval $backupCam

