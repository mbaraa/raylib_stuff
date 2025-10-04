.PHONY: dvd pong clean

dvd:
	pushd ./dvd_screen; \
	make run; \
	popd

pong:
	pushd ./pong; \
	make run; \
	popd

clean:
	for dir in `ls` ; do \
		if [[ -d $$dir ]] ; then \
			pushd $$dir ; \
			make clean ; \
			popd ; \
		fi \
	done

