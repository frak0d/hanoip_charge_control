#!/system/bin/sh

if [ ! "$1" ]; then
    echo "\e[1;91mError: Level Not provided!\e[0m"
    exit -1
fi

BATTERY=/sys/devices/platform/soc/c440000.qcom,spmi/spmi-0/spmi0-00/c440000.qcom,spmi:qcom,pm6150@0:qcom,qpnp-smb5/power_supply/battery

echo $1 > $BATTERY/charge_control_limit
echo "\e[1;94mCurrent limit set to $(($(cat $BATTERY/constant_charge_current) / 1000)) mA\e[0m"

#-# script by 0xB00B #-#
