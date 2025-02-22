AUTOMAKE_OPTIONS = foreign subdir-objects


bin_PROGRAMS = my_hash_project


my_hash_project_SOURCES = src/main.c src/hasher.c
my_hash_project_CPPFLAGS = -I$(top_srcdir)/include
my_hash_project_LDADD = $(OPENSSL_LIBS)


ACLOCAL_AMFLAGS = -I m4
