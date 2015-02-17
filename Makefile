SUBDIRS = rgb_single rgb_3pixel hsv_single avg_ambient

.PHONY: subdirs $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@
