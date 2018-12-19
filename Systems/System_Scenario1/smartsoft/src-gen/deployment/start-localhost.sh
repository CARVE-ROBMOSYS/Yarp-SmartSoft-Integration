#!/bin/sh
#--------------------------------------------------------------------------
# Code generated by the SmartSoft MDSD Toolchain
# The SmartSoft Toolchain has been developed by:
#  
# Service Robotics Research Center
# University of Applied Sciences Ulm
# Prittwitzstr. 10
# 89075 Ulm (Germany)
#
# Information about the SmartSoft MDSD Toolchain is available at:
# www.servicerobotik-ulm.de
#
# Please do not modify this file. It will be re-generated
# running the code generator.
#--------------------------------------------------------------------------
#
# start script for device localhost


PID_XTERM="/var/tmp/start-localhost-xterms.pid"
PID_COMPONENT_NAMES="/var/tmp/start-localhost-component-names.pid"

SCRIPT_DIR=`pwd`
SCRIPT_NAME=start-localhost.sh

export SMART_ROOT_DEPLOYMENT=$SCRIPT_DIR

#######
## case
case "$1" in
	    
	    
#########################################################################################
## start
start)

true > $PID_XTERM
true > $PID_COMPONENT_NAMES

echo "Starting scenario..."
date -R

# CONFIGURE NAMING SERVICE
	export SMART_NS_ADDR=127.0.0.1:20002

echo "Stopping Naming Service..."
killall AceSmartSoftNamingService &
test -e SMART_NAMES && rm -f SMART_NAMES
sleep 1
echo Starting Naming Service...
rm -f AceSmartSoftNamingService.log
xterm -l -lf AceSmartSoftNamingService.log -title "AceSmartSoftNamingService" -hold -e "export LD_LIBRARY_PATH=$SCRIPT_DIR:\$LD_LIBRARY_PATH; ./NamingService/AceSmartSoftNamingService --ns-port 20002 --ns-dir ./ --ns-file SMART_NAMES --filename=ns_config.ini; echo; echo; echo 'Naming Service exited'; /bin/bash" &
echo $! >> $PID_XTERM
echo AceSmartSoftNamingService >> $PID_COMPONENT_NAMES
sleep 1

## start components
export SMART_IP=127.0.0.1
echo "starting components..."

# Component instance BT_runner
echo
echo "############################################"
echo "## Starting component instance BT_runner"
cd $SCRIPT_DIR
echo "executing startstop-hooks-BT_runner.sh (errors might be ignored)"
bash startstop-hooks-BT_runner.sh pre-start
cd $SCRIPT_DIR/BT_runner_data
rm -f "../BT_runner.log"
xterm -l -lf "../BT_runner.log" -title "BT_runner@localhost Component" -hold -e "export LD_LIBRARY_PATH=$SCRIPT_DIR:\$LD_LIBRARY_PATH; $SCRIPT_DIR/BT_runner -filename=$SCRIPT_DIR/BT_runner.ini; echo; echo; echo 'BT_runner exited.'; echo; /bin/bash --login" &
echo $! >> $PID_XTERM
echo BT_runner >> $PID_COMPONENT_NAMES
cd $SCRIPT_DIR
bash startstop-hooks-BT_runner.sh post-start
echo -e "\n\n\n"

# Component instance BT_tickDispatcher
echo
echo "############################################"
echo "## Starting component instance BT_tickDispatcher"
cd $SCRIPT_DIR
echo "executing startstop-hooks-BT_tickDispatcher.sh (errors might be ignored)"
bash startstop-hooks-BT_tickDispatcher.sh pre-start
cd $SCRIPT_DIR/BT_tickDispatcher_data
rm -f "../BT_tickDispatcher.log"
xterm -l -lf "../BT_tickDispatcher.log" -title "BT_tickDispatcher@localhost Component" -hold -e "export LD_LIBRARY_PATH=$SCRIPT_DIR:\$LD_LIBRARY_PATH; $SCRIPT_DIR/BT_tickDispatcher -filename=$SCRIPT_DIR/BT_tickDispatcher.ini; echo; echo; echo 'BT_tickDispatcher exited.'; echo; /bin/bash --login" &
echo $! >> $PID_XTERM
echo BT_tickDispatcher >> $PID_COMPONENT_NAMES
cd $SCRIPT_DIR
bash startstop-hooks-BT_tickDispatcher.sh post-start
echo -e "\n\n\n"

# Component instance GraspingSkill
echo
echo "############################################"
echo "## Starting component instance GraspingSkill"
cd $SCRIPT_DIR
echo "executing startstop-hooks-GraspingSkill.sh (errors might be ignored)"
bash startstop-hooks-GraspingSkill.sh pre-start
cd $SCRIPT_DIR/GraspingSkill_data
rm -f "../GraspingSkill.log"
xterm -l -lf "../GraspingSkill.log" -title "GraspingSkill@localhost Component" -hold -e "export LD_LIBRARY_PATH=$SCRIPT_DIR:\$LD_LIBRARY_PATH; $SCRIPT_DIR/GraspingSkill -filename=$SCRIPT_DIR/GraspingSkill.ini; echo; echo; echo 'GraspingSkill exited.'; echo; /bin/bash --login" &
echo $! >> $PID_XTERM
echo GraspingSkill >> $PID_COMPONENT_NAMES
cd $SCRIPT_DIR
bash startstop-hooks-GraspingSkill.sh post-start
echo -e "\n\n\n"

# Component instance Navigationskill
echo
echo "############################################"
echo "## Starting component instance Navigationskill"
cd $SCRIPT_DIR
echo "executing startstop-hooks-Navigationskill.sh (errors might be ignored)"
bash startstop-hooks-Navigationskill.sh pre-start
cd $SCRIPT_DIR/Navigationskill_data
rm -f "../Navigationskill.log"
xterm -l -lf "../Navigationskill.log" -title "Navigationskill@localhost Component" -hold -e "export LD_LIBRARY_PATH=$SCRIPT_DIR:\$LD_LIBRARY_PATH; $SCRIPT_DIR/YarpNavigationClient -filename=$SCRIPT_DIR/Navigationskill.ini; echo; echo; echo 'Navigationskill exited.'; echo; /bin/bash --login" &
echo $! >> $PID_XTERM
echo YarpNavigationClient >> $PID_COMPONENT_NAMES
cd $SCRIPT_DIR
bash startstop-hooks-Navigationskill.sh post-start
echo -e "\n\n\n"

# Component instance VisionSkill
echo
echo "############################################"
echo "## Starting component instance VisionSkill"
cd $SCRIPT_DIR
echo "executing startstop-hooks-VisionSkill.sh (errors might be ignored)"
bash startstop-hooks-VisionSkill.sh pre-start
cd $SCRIPT_DIR/VisionSkill_data
rm -f "../VisionSkill.log"
xterm -l -lf "../VisionSkill.log" -title "VisionSkill@localhost Component" -hold -e "export LD_LIBRARY_PATH=$SCRIPT_DIR:\$LD_LIBRARY_PATH; $SCRIPT_DIR/VisionSkill -filename=$SCRIPT_DIR/VisionSkill.ini; echo; echo; echo 'VisionSkill exited.'; echo; /bin/bash --login" &
echo $! >> $PID_XTERM
echo VisionSkill >> $PID_COMPONENT_NAMES
cd $SCRIPT_DIR
bash startstop-hooks-VisionSkill.sh post-start
echo -e "\n\n\n"


cd $SCRIPT_DIR

;; ## start


#########################################################################################
## stop
stop)
cd $SCRIPT_DIR
bash startstop-hooks-BT_runner.sh pre-stop
bash startstop-hooks-BT_tickDispatcher.sh pre-stop
bash startstop-hooks-GraspingSkill.sh pre-stop
bash startstop-hooks-Navigationskill.sh pre-stop
bash startstop-hooks-VisionSkill.sh pre-stop

echo "kill all components..."

for I in `cat $PID_COMPONENT_NAMES`; do
        echo $I
        killall -2 $I
done
rm $PID_COMPONENT_NAMES

sleep 3

for I in `cat $PID_XTERM`; do
        echo $I
        kill -2 $I
done
rm $PID_XTERM



test -e SMART_NAMES && rm -f SMART_NAMES

bash startstop-hooks-BT_runner.sh post-stop
bash startstop-hooks-BT_tickDispatcher.sh post-stop
bash startstop-hooks-GraspingSkill.sh post-stop
bash startstop-hooks-Navigationskill.sh post-stop
bash startstop-hooks-VisionSkill.sh post-stop


# collect log files
ls -l *.log && (
	pwd
	tar czvf localhost-logs-$(date +"%Y%m%d%H%M").tar.gz *.log
	rm *.log
)

;; ## stop



#########################################################################################
## menu

menu-start)
	bash $SCRIPT_NAME start
	cd $SCRIPT_DIR
	bash $SCRIPT_NAME menu
;;

menu-stop)
	bash $SCRIPT_NAME stop
	cd $SCRIPT_DIR
	bash $SCRIPT_NAME menu
;;

menu-tile)
	bash tiler.sh
	cd $SCRIPT_DIR
	bash $SCRIPT_NAME menu
;;

menu)

#wmctrl -r :ACTIVE: -b add,above
ACTION=$(whiptail --title "Scenario Control" --menu "Choose an option" 12 35 4 "menu-start" "Start Scenario" "menu-stop" "Stop Scenario" "menu-tile" "Arrange terminals" "quit" "Quit to console" 3>&1 1>&2 2>&3)
#whiptail --title "Scenario Control" --menu "Choose an option" 10 30 3 "menu-start" "Start Scenario" "menu-stop" "Stop Scenario" "quit" "Quit to console" 2>/tmp/whip
#ACTION=`cat /tmp/whip`

cd $SCRIPT_DIR
bash $SCRIPT_NAME $ACTION

;; ## menu

quit)
	bash $SCRIPT_NAME stop
;;
		
		
#########################################################################################
## default
*)
echo "No such parameter: $1"
echo "Usage: $SCRIPT_NAME {start|stop|menu-start|menu-stop|menu}"
exit 1
;;

esac