.PHONY: dvd pong snake clock clean

dvd:
	pushd ./dvd_screen; \
	make run; \
	popd

pong:
	pushd ./pong; \
	make run; \
	popd

snake:
	pushd ./snake; \
	make run; \
	popd

clock:
	pushd ./clock; \
	make run; \
	popd

clean:
	@for dir in `ls` ; do \
		if [[ -d $$dir ]] ; then \
			pushd $$dir ; \
			make clean ; \
			popd ; \
		fi \
	done

