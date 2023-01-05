# Object : The example of LCD1602 i2c proc driver and clock application

![pic](demo.jpg)<br><br><br>


## Test HW: Linkit 7688
## Test SW: openwrit 3.18.109

## Usage:
	copy lcd1602i2c2 to openwrt/package/kernel
	make menuconfig
		select
		Kernel modules
		Other modules
		[*]kmod-lcd1602i2c2
	make package/lcd1602i2c2/compile V=s
	opkg install ipk to Linkit 7688

	echo -e -n "\n0123456" > /proc/LCDI2C
	The LCD1602 shwo 0123456

	echo -e -n "\b" > /proc/LCDI2C
	The LCD1602 turn off backlight

	echo -e -n "\a" > /proc/LCDI2C
	The LCD1602 turn on backlight

---


	copy clock_gcat to openwrt/package/
	copy clock_gcat_set_autorun to openwrt/package/
	make menuconfig
		select
		Utilities
		[*]clock_gcat
		[*]clock_gcat_set_autorun
	make package/clock_gcat/compile V=s
	make package/clock_gcat_set_autorun/compile V=s
	opkg install ipk to Linkit 7688

	reboot Linkit 7688 and LCD show time.

If the code help you, how about buy street cat a fish can ?
