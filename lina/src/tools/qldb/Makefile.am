INCLUDES = -I$(top_srcdir)/include $(QT_INCLUDES) $(all_includes)
METASOURCES = AUTO
bin_PROGRAMS =  qldb
UIFILES = qldb_dlg.ui
MOCFILES = qldb_dlg.cpp qldb_dlg.h
qldb_SOURCES =  $(UIFILES:.ui=.h) $(UIFILES:.ui=.cpp) $(MOCFILES:.cpp=_moc.cpp) qldb.cpp

%.h: %.ui
	$(UIC) $< -o $@
%.cpp: %.h %.ui
	$(UIC) -impl $^ -o $@
%_moc.cpp: %.h
	$(MOC) -o $@ $<

qldb_LDADD = $(top_builddir)/lib/liblina.a $(QT_LDFLAGS) $(QT_LIB)
