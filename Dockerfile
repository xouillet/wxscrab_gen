FROM alpine:3.15

RUN apk --update add musl-dev gcc scons

WORKDIR /app
COPY . /app

RUN	scons install system=1

RUN rm -rf /app

EXPOSE 1964
CMD /usr/bin/gen_part
