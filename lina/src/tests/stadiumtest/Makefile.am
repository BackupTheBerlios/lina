INCLUDES = -I$(top_srcdir)/include $(QT_INCLUDES) $(all_includes)
METASOURCES = AUTO
bin_PROGRAMS =  stadiumtest
UIFILES = stadiumtest_dlg.ui
MOCFILES = stadiumtest_dlg.cpp stadiumtest_dlg.h
stadiumtest_LDADD = $(top_builddir)/lib/liblina.a $(QT_LIB) $(QT_LDFLAGS)
stadiumtest_SOURCES = $(UIFILES:.ui=.h) $(UIFILES:.ui=.cpp) $(MOCFILES:.cpp=_moc.cpp) stadiumtest.cpp

%.h: %.ui
	$(UIC) $< -o $@
%.cpp: %.h %.ui
	$(UIC) -impl $^ -o $@
%_moc.cpp: %.h
	$(MOC) -o $@ $<
noinst_HEADERS =  stadiumtest_dlg.ui
