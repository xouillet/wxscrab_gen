build:
	docker build -t philippechataignon/wxscrab_gen:build .
tag:
	docker tag philippechataignon/wxscrab_gen:build philippechataignon/wxscrab_gen
run:
	docker run -d --name wxscrab_gen -p 127.0.0.1:1964:1964 philippechataignon/wxscrab_gen
stop:
	docker rm -f wxscrab_gen
log:
	docker logs wxscrab_gen
