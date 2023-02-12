FROM alpine:3.15

RUN apk --update add musl-dev gcc scons pkgconfig libmicrohttpd-dev

WORKDIR /app
COPY . /app

RUN	scons install system=1

RUN rm -rf /app

EXPOSE 1964
CMD /usr/bin/scrab_server
