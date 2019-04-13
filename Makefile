all:
	make -C src
	make -C test/wrap
	make -C test

clean:
	make -C src clean
	make -C test/wrap clean
	make -C test clean
	@rm -rf cov_output *.info 2>/dev/null
