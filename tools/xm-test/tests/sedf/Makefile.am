SUBDIRS =

TESTS = 01_sedf_period_slice_pos.test \
        02_sedf_period_lower_neg.test \
        03_sedf_slice_lower_neg.test  \
        04_sedf_slice_upper_neg.test  \
        05_sedf_extratime_pos.test    \
        06_sedf_extratime_disable_neg.test

XFAIL_TESTS = 

EXTRA_DIST = $(TESTS) $(XFAIL_TESTS)

TESTS_ENVIRONMENT=@TENV@

%.test: %.py
	cp $< $@
	chmod +x $@

clean-local: am_config_clean-local

am_config_clean-local:
	rm -f *test
	rm -f *log
	rm -f *~
