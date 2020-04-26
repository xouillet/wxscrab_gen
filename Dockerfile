FROM alpine:3.11.5

RUN apk --update add musl-dev gcc python3 python3-dev scons swig py3-bottle py3-gunicorn
COPY . /app
RUN	ln -sf /usr/bin/python3 /usr/bin/python ;\
    cd /app/gen ;\
	scons ;\
	swig -python dic.i ;\
    python3 setup.py install
EXPOSE 1964
ENTRYPOINT /bin/sh -c "cd /app/server ; python3 server.py"
