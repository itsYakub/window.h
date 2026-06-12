# ========

# root directory of the makefile
MK_ROOT	= $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
MK_NAME = window

# ========

.PHONY : all

all : install 

.PHONY : install

install :
	mkdir -p /usr/local/include/$(MK_NAME)/
	cp -f $(MK_ROOT)$(MK_NAME).h /usr/local/include/$(MK_NAME)/
	ln -nfs /usr/local/include/$(MK_NAME)/$(MK_NAME).h /usr/local/include/$(MK_NAME).h

.PHONY : remove

remove :
	rm -fr /usr/local/include/$(MK_NAME)
	rm -f  /usr/local/include/$(MK_NAME).h

.PHONY : samples

samples :
	make -C $(MK_ROOT)samples/

# ========
