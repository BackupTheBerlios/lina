INCLUDES = -I$(top_srcdir)/include $(all_includes) $(QT_INCLUDES)
METASOURCES = AUTO
bin_PROGRAMS =  lchat lchatd
UIFILES = linachat.ui
MOCFILES = linachat.cpp linachat.h
lchat_LDADD = $(top_builddir)/lib/liblina.a $(top_builddir)/lib/netxx/libnetxx.a -lssl $(QT_LIB) $(QT_LDFLAGS)
lchat_SOURCES =  $(UIFILES:.ui=.h) $(UIFILES:.ui=.cpp) $(MOCFILES:.cpp=_moc.cpp) lchat.cpp lchat.h
noinst_HEADERS =  lchat.h lchatd.h linachat.ui
lchatd_SOURCES =  lchatd.cpp lchatd.h
lchatd_LDADD = $(top_builddir)/lib/liblina.a $(top_builddir)/lib/netxx/libnetxx.a -lssl

%.h: %.ui
	$(UIC) $< -o $@
%.cpp: %.h %.ui
	$(UIC) -impl $^ -o $@
%_moc.cpp: %.h
	$(MOC) -o $@ $<