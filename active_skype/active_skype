#!/bin/bash

#####################below functions need be adjusted when environment changed

filter_tray_window()
{
    xprop -id $1 WM_NORMAL_HINTS | grep minimum | grep '22 by 22' > /dev/null
}

filter_main_window()
{
    xprop -id $1 WM_NORMAL_HINTS| grep minimum| grep "240 by " > /dev/null
}

show_message()
{
    #save and move current main window position
    eval local `xdotool getwindowgeometry --shell $1 | grep -P 'X|Y'`
    xdotool windowmove $1 0 0

    #find and show recent contact 
    xdotool windowraise $1 mousemove --sync --window $1 167 15 click --repeat 1 1
    xdotool mousemove_relative --sync 0 22
    sleep 0.3
    xdotool mousemove_relative --sync 200 0
    xdotool click 1

    #restore main window position
    xdotool windowmove $1 $X $Y
}


######################


search_windows()
{
    xdotool search --onlyvisible skype 2>/dev/null
}

active_main_window()
{
    xdotool click --window `find_window "filter_tray_window"` 1
    echo xdotool click --window `find_window "filter_tray_window"` 1
}

find_window()
{
    for w in `search_windows`; do
	if ${1} $w
	then
	    echo $w
	fi
    done
}

record_position()
{
    eval `xdotool getmouselocation --shell | grep -P 'X|Y'`
}
restroe_position()
{
    #$X and $Y was blessed in record_position
    xdotool mousemove $X $Y
}

######################logical codes################

record_position
has_main_window=`find_window "filter_main_window"`

if [ -z $has_main_window ]
then
    active_main_window
fi

show_message `find_window "filter_main_window"`

restroe_position

if [ -z $has_main_window ]
then
    echo "Try restore main window status"
    xdotool click --window `find_window "filter_tray_window"` --repeat 2 1
fi
