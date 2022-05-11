include $(TOPDIR)/rules.mk

PKG_NAME:=clock_gcat
PKG_RELEASE:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk


define Package/$(PKG_NAME)
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=clock_gcat 
endef

define Package/$(PKG_NAME)/description
  clock_gcat is for I2C LCD 1602
endef

define Build/Compile
  $(MAKE) -v
endef


#define Build/Prepare
#	mkdir -p $(PKG_BUILD_DIR)
#	$(CP) ./src/* $(PKG_BUILD_DIR)
#endef


define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/usr/bin/
	$(INSTALL_BIN) ./files/clock_gcat1.sh $(1)/usr/bin/
endef


$(eval $(call BuildPackage,$(PKG_NAME)))
