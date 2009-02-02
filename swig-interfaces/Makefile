#
# This makefile is used to generate the wrapper code from the
# SWIG interface files.
#
# $Id: Makefile 2837 2008-03-28 21:30:30Z lyle $
#

.PHONY: clean

SWIG = /opt/local/bin/swig

#
#  Using the following command-line flags:
#
# -nodefaultctor don't generate default constructors for classes that don't declare them
# -nodefaultdtor don't generate default destructors for classes that don't declare them
# -w302 seems to be required to suppress bogus SWIG warnings about redefined identifiers
# -features compactdefaultargs causes SWIG to default to the old code generation method for functions with default arguments
#

SWIGFLAGS = -fcompact -c++ -ruby -nodefaultdtor -nodefaultctor -w302 -features compactdefaultargs -I../fox-includes
SRCDIR = ../ext/fox16
SED = sed -f swig.sed
RUBY = ruby

MODULES = \
	core_wrap.cxx \
	dc_wrap.cxx \
	dialogs_wrap.cxx \
	frames_wrap.cxx \
	iconlist_wrap.cxx \
	icons_wrap.cxx \
	image_wrap.cxx \
	label_wrap.cxx \
	layout_wrap.cxx \
	list_wrap.cxx \
	mdi_wrap.cxx \
	menu_wrap.cxx \
	fx3d_wrap.cxx \
	scintilla_wrap.cxx \
	table_wrap.cxx \
	text_wrap.cxx \
	treelist_wrap.cxx \
	ui_wrap.cxx

all: $(SRCDIR)/include/swigrubyrun.h $(MODULES)

core_wrap.cxx: core.i
	$(SWIG) $(SWIGFLAGS) -o core_wrap.cxx core.i
	$(SWIG) $(SWIGFLAGS) -MM core.i > core_wrap.d
	$(SED) core_wrap.cxx > junk; mv junk $(SRCDIR)/core_wrap.cpp

dc_wrap.cxx: dcmodule.i
	$(SWIG) $(SWIGFLAGS) -o dc_wrap.cxx dcmodule.i
	$(SWIG) $(SWIGFLAGS) -MM dcmodule.i > dcmodule_wrap.d
	$(SED) dc_wrap.cxx > junk; mv junk $(SRCDIR)/dc_wrap.cpp

dialogs_wrap.cxx: dialogs.i
	$(SWIG) $(SWIGFLAGS) -o dialogs_wrap.cxx dialogs.i
	$(SWIG) $(SWIGFLAGS) -MM dialogs.i > dialogs_wrap.d
	$(SED) dialogs_wrap.cxx > junk; mv junk $(SRCDIR)/dialogs_wrap.cpp

frames_wrap.cxx: framesmodule.i
	$(SWIG) $(SWIGFLAGS) -o frames_wrap.cxx framesmodule.i
	$(SWIG) $(SWIGFLAGS) -MM framesmodule.i > framesmodule_wrap.d
	$(SED) frames_wrap.cxx > junk; mv junk $(SRCDIR)/frames_wrap.cpp

iconlist_wrap.cxx: iconlistmodule.i
	$(SWIG) $(SWIGFLAGS) -o iconlist_wrap.cxx iconlistmodule.i
	$(SWIG) $(SWIGFLAGS) -MM iconlistmodule.i > iconlistmodule_wrap.d
	$(SED) iconlist_wrap.cxx > junk; mv junk $(SRCDIR)/iconlist_wrap.cpp

icons_wrap.cxx: icons.i
	$(SWIG) $(SWIGFLAGS) -o icons_wrap.cxx icons.i
	$(SWIG) $(SWIGFLAGS) -MM icons.i > icons_wrap.d
	$(SED) icons_wrap.cxx > junk; mv junk $(SRCDIR)/icons_wrap.cpp

image_wrap.cxx: image.i
	$(SWIG) $(SWIGFLAGS) -o image_wrap.cxx image.i
	$(SWIG) $(SWIGFLAGS) -MM image.i > image_wrap.d
	$(SED) image_wrap.cxx > junk; mv junk $(SRCDIR)/image_wrap.cpp

label_wrap.cxx: labelmodule.i
	$(SWIG) $(SWIGFLAGS) -o label_wrap.cxx labelmodule.i
	$(SWIG) $(SWIGFLAGS) -MM labelmodule.i > labelmodule_wrap.d
	$(SED) label_wrap.cxx > junk; mv junk $(SRCDIR)/label_wrap.cpp

layout_wrap.cxx: layout.i
	$(SWIG) $(SWIGFLAGS) -o layout_wrap.cxx layout.i
	$(SWIG) $(SWIGFLAGS) -MM layout.i > layout_wrap.d
	$(SED) layout_wrap.cxx > junk; mv junk $(SRCDIR)/layout_wrap.cpp

list_wrap.cxx: listmodule.i
	$(SWIG) $(SWIGFLAGS) -o list_wrap.cxx listmodule.i
	$(SWIG) $(SWIGFLAGS) -MM listmodule.i > listmodule_wrap.d
	$(SED) list_wrap.cxx > junk; mv junk $(SRCDIR)/list_wrap.cpp

mdi_wrap.cxx: mdi.i
	$(SWIG) $(SWIGFLAGS) -o mdi_wrap.cxx mdi.i
	$(SWIG) $(SWIGFLAGS) -MM mdi.i > mdi_wrap.d
	$(SED) mdi_wrap.cxx > junk; mv junk $(SRCDIR)/mdi_wrap.cpp

menu_wrap.cxx: menumodule.i
	$(SWIG) $(SWIGFLAGS) -o menu_wrap.cxx menumodule.i
	$(SWIG) $(SWIGFLAGS) -MM menumodule.i > menumodule_wrap.d
	$(SED) menu_wrap.cxx > junk; mv junk $(SRCDIR)/menu_wrap.cpp

fx3d_wrap.cxx: fx3d.i
	$(SWIG) $(SWIGFLAGS) -o fx3d_wrap.cxx fx3d.i
	$(SWIG) $(SWIGFLAGS) -MM fx3d.i > fx3d_wrap.d
	$(SED) fx3d_wrap.cxx > junk; mv junk $(SRCDIR)/fx3d_wrap.cpp

scintilla_wrap.cxx: scintilla.i
	$(SWIG) $(SWIGFLAGS) -o scintilla_wrap.cxx scintilla.i
	$(SWIG) $(SWIGFLAGS) -MM scintilla.i > scintilla_wrap.d
	$(SED) scintilla_wrap.cxx > junk; mv junk $(SRCDIR)/scintilla_wrap.cpp

table_wrap.cxx: table-module.i
	$(SWIG) $(SWIGFLAGS) -o table_wrap.cxx table-module.i
	$(SWIG) $(SWIGFLAGS) -MM table-module.i > table-module_wrap.d
	$(SED) table_wrap.cxx > junk; mv junk $(SRCDIR)/table_wrap.cpp

text_wrap.cxx: text-module.i
	$(SWIG) $(SWIGFLAGS) -o text_wrap.cxx text-module.i
	$(SWIG) $(SWIGFLAGS) -MM text-module.i > text-module_wrap.d
	$(SED) text_wrap.cxx > junk; mv junk $(SRCDIR)/text_wrap.cpp

treelist_wrap.cxx: treelist-module.i
	$(SWIG) $(SWIGFLAGS) -o treelist_wrap.cxx treelist-module.i
	$(SWIG) $(SWIGFLAGS) -MM treelist-module.i > treelist-module_wrap.d
	$(SED) treelist_wrap.cxx > junk; mv junk $(SRCDIR)/treelist_wrap.cpp

ui_wrap.cxx: ui.i
	$(SWIG) $(SWIGFLAGS) -o ui_wrap.cxx ui.i
	$(SWIG) $(SWIGFLAGS) -MM ui.i > ui_wrap.d
	$(SED) ui_wrap.cxx > junk; mv junk $(SRCDIR)/ui_wrap.cpp

$(SRCDIR)/include/swigrubyrun.h:
	$(SWIG) -ruby -external-runtime $(SRCDIR)/include/swigrubyrun.h

clean:
	@rm -f $(SRCDIR)/include/swigrubyrun.h $(MODULES) *.d

-include $(MODULES:.cxx=.d)
