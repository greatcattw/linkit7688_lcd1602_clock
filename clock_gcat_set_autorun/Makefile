include $(TOPDIR)/rules.mk

PKG_NAME:=clock_gcat_set_autorun
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


define Package/$(PKG_NAME)/preinst
  #!/bin/sh
  echo "ready to install $(PKG_NAME)"
endef

define Package/$(PKG_NAME)/postinst
  #!/bin/sh
  echo "ok to install $(PKG_NAME)"
  if [ -z "$${IPKG_INSTROOT}" ]; then
    /etc/init.d/clock_gcat enable
  fi

endef

define Package/$(PKG_NAME)/prerm
  #!/bin/sh
  echo "ready to remove $(PKG_NAME)"
  if [ -z "$${IPKG_INSTROOT}" ]; then
    /etc/init.d/clock_gcat disable
  fi
endef

define Package/$(PKG_NAME)/postrm
  #!/bin/sh
  echo "ok to remove $(PKG_NAME)"
endef

#define Build/Prepare
#	mkdir -p $(PKG_BUILD_DIR)
#	$(CP) ./src/* $(PKG_BUILD_DIR)
#endef


define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) ./files/clock_gcat.autorun $(1)/etc/init.d/clock_gcat
endef


$(eval $(call BuildPackage,$(PKG_NAME)))
