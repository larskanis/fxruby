#
# This makefile is used to generate the wrapper code from the
# SWIG interface files.
#
# $Id: Makefile 2827 2008-03-28 16:04:44Z lyle $
#

.PHONY: clean

SWIG = /usr/local/bin/swig
SWIGFLAGS = -fcompact -noruntime -c++ -ruby -no_default -I../fox-includes
SRCDIR = ../ext/fox16
SED = sed -f swig.sed
RUBY = ruby
SWIGLIB := $(shell /usr/local/bin/swig -swiglib)

MODULES = \
	$(SRCDIR)/core_wrap.cpp \
	$(SRCDIR)/dc_wrap.cpp \
	$(SRCDIR)/dialogs_wrap.cpp \
	$(SRCDIR)/frames_wrap.cpp \
	$(SRCDIR)/iconlist_wrap.cpp \
	$(SRCDIR)/icons_wrap.cpp \
	$(SRCDIR)/image_wrap.cpp \
	$(SRCDIR)/label_wrap.cpp \
	$(SRCDIR)/layout_wrap.cpp \
	$(SRCDIR)/list_wrap.cpp \
	$(SRCDIR)/mdi_wrap.cpp \
	$(SRCDIR)/menu_wrap.cpp \
	$(SRCDIR)/fx3d_wrap.cpp \
	$(SRCDIR)/scintilla_wrap.cpp \
	$(SRCDIR)/table_wrap.cpp \
	$(SRCDIR)/text_wrap.cpp \
	$(SRCDIR)/treelist_wrap.cpp \
	$(SRCDIR)/ui_wrap.cpp

all: $(SRCDIR)/librb.c $(MODULES)

$(SRCDIR)/core_wrap.cpp: core.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/core_wrap.cpp core.i
	$(SED) $(SRCDIR)/core_wrap.cpp > junk; mv junk $(SRCDIR)/core_wrap.cpp

$(SRCDIR)/dc_wrap.cpp: dcmodule.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/dc_wrap.cpp dcmodule.i
	$(SED) $(SRCDIR)/dc_wrap.cpp > junk; mv junk $(SRCDIR)/dc_wrap.cpp

$(SRCDIR)/dialogs_wrap.cpp: dialogs.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/dialogs_wrap.cpp dialogs.i
	$(SED) $(SRCDIR)/dialogs_wrap.cpp > junk; mv junk $(SRCDIR)/dialogs_wrap.cpp

$(SRCDIR)/frames_wrap.cpp: framesmodule.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/frames_wrap.cpp framesmodule.i
	$(SED) $(SRCDIR)/frames_wrap.cpp > junk; mv junk $(SRCDIR)/frames_wrap.cpp

$(SRCDIR)/iconlist_wrap.cpp: iconlistmodule.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/iconlist_wrap.cpp iconlistmodule.i
	$(SED) $(SRCDIR)/iconlist_wrap.cpp > junk; mv junk $(SRCDIR)/iconlist_wrap.cpp

$(SRCDIR)/icons_wrap.cpp: icons.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/icons_wrap.cpp icons.i
	$(SED) $(SRCDIR)/icons_wrap.cpp > junk; mv junk $(SRCDIR)/icons_wrap.cpp

$(SRCDIR)/image_wrap.cpp: image.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/image_wrap.cpp image.i
	$(SED) $(SRCDIR)/image_wrap.cpp > junk; mv junk $(SRCDIR)/image_wrap.cpp

$(SRCDIR)/label_wrap.cpp: labelmodule.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/label_wrap.cpp labelmodule.i
	$(SED) $(SRCDIR)/label_wrap.cpp > junk; mv junk $(SRCDIR)/label_wrap.cpp

$(SRCDIR)/layout_wrap.cpp: layout.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/layout_wrap.cpp layout.i
	$(SED) $(SRCDIR)/layout_wrap.cpp > junk; mv junk $(SRCDIR)/layout_wrap.cpp

$(SRCDIR)/list_wrap.cpp: listmodule.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/list_wrap.cpp listmodule.i
	$(SED) $(SRCDIR)/list_wrap.cpp > junk; mv junk $(SRCDIR)/list_wrap.cpp

$(SRCDIR)/mdi_wrap.cpp: mdi.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/mdi_wrap.cpp mdi.i
	$(SED) $(SRCDIR)/mdi_wrap.cpp > junk; mv junk $(SRCDIR)/mdi_wrap.cpp

$(SRCDIR)/menu_wrap.cpp: menumodule.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/menu_wrap.cpp menumodule.i
	$(SED) $(SRCDIR)/menu_wrap.cpp > junk; mv junk $(SRCDIR)/menu_wrap.cpp

$(SRCDIR)/fx3d_wrap.cpp: fx3d.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/fx3d_wrap.cpp fx3d.i
	$(SED) $(SRCDIR)/fx3d_wrap.cpp > junk; mv junk $(SRCDIR)/fx3d_wrap.cpp

$(SRCDIR)/scintilla_wrap.cpp: scintilla.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/scintilla_wrap.cpp scintilla.i
	$(SED) $(SRCDIR)/scintilla_wrap.cpp > junk; mv junk $(SRCDIR)/scintilla_wrap.cpp

$(SRCDIR)/table_wrap.cpp: table-module.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/table_wrap.cpp table-module.i
	$(SED) $(SRCDIR)/table_wrap.cpp > junk; mv junk $(SRCDIR)/table_wrap.cpp

$(SRCDIR)/text_wrap.cpp: text-module.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/text_wrap.cpp text-module.i
	$(SED) $(SRCDIR)/text_wrap.cpp > junk; mv junk $(SRCDIR)/text_wrap.cpp

$(SRCDIR)/treelist_wrap.cpp: treelist-module.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/treelist_wrap.cpp treelist-module.i
	$(SED) $(SRCDIR)/treelist_wrap.cpp > junk; mv junk $(SRCDIR)/treelist_wrap.cpp

$(SRCDIR)/ui_wrap.cpp: ui.i
	$(SWIG) $(SWIGFLAGS) -o $(SRCDIR)/ui_wrap.cpp ui.i
	$(SED) $(SRCDIR)/ui_wrap.cpp > junk; mv junk $(SRCDIR)/ui_wrap.cpp

$(SRCDIR)/librb.c: $(SWIGLIB)/ruby/precommon.swg $(SWIGLIB)/common.swg $(SWIGLIB)/ruby/rubyhead.swg $(SWIGLIB)/ruby/rubydef.swg
	@echo "#define SWIG_GLOBAL 1" > $(SRCDIR)/librb.c
	@cat $(SWIGLIB)/ruby/precommon.swg $(SWIGLIB)/common.swg $(SWIGLIB)/ruby/rubyhead.swg $(SWIGLIB)/ruby/rubydef.swg >> $(SRCDIR)/librb.c

clean:
	@rm -f $(SRCDIR)/librb.c $(MODULES)

depend:
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/core_wrap.cpp core.i > dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/dc_wrap.cpp dcmodule.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/dialogs_wrap.cpp dialogs.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/frames_wrap.cpp framesmodule.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/iconlist_wrap.cpp iconlistmodule.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/icons_wrap.cpp icons.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/image_wrap.cpp image.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/label_wrap.cpp labelmodule.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/layout_wrap.cpp layout.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/list_wrap.cpp listmodule.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/mdi_wrap.cpp mdi.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/menu_wrap.cpp menumodule.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/fx3d_wrap.cpp fx3d.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/scintilla_wrap.cpp scintilla.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/table_wrap.cpp table-module.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/text_wrap.cpp text-module.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/treelist_wrap.cpp treelist-module.i >> dependencies
	$(SWIG) $(SWIGFLAGS) -MM -o $(SRCDIR)/ui_wrap.cpp ui.i >> dependencies

include dependencies
