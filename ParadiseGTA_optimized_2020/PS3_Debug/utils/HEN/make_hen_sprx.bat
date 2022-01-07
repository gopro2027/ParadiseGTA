@echo OFF
unfself ../ParadiseGTA.sprx ParadiseGTA.prx
C:
cd C:\Users\Ty\ps3tools\ps3tools\tools\scetool\
echo rel path is %~dp0
scetool --sce-type=SELF --compress-data=TRUE --skip-sections=FALSE --key-revision=04 --self-ctrl-flags=4000000000000000000000000000000000000000000000000000000000000002 --self-auth-id=1010000001000003 --self-add-shdrs=TRUE --self-vendor-id=01000002 --self-app-version=0001000000000000 --self-type=APP   --self-fw-version=0003004000000000 --encrypt "%~dp0ParadiseGTA.prx" "%~dp0ParadiseGTA.sprx"
D:
cd "%~dp0"


echo user anonymous> ftpcmd.dat
echo anonymous>> ftpcmd.dat
echo bin>> ftpcmd.dat
echo cd /dev_hdd0/tmp/>> ftpcmd.dat
echo put ParadiseGTA.sprx>> ftpcmd.dat
echo quit>> ftpcmd.dat
ftp -n -s:ftpcmd.dat 192.168.1.72 
del ftpcmd.dat

PAUSE