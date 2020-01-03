#FROM bk.artifactory.oa.com:8090/paas/public/tlinux2.2-bridge-tcloud-underlay:latest
FROM debian:stretch-slim

# 时区
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime

ENV LANG=zh_CN.UTF-8 \
    LANGUAGE=zh_CN:zh \
    LC_ALL=zh_CN.UTF-8

RUN mkdir -p /usr/local/app/vcms-go/demo

WORKDIR /usr/local/app/vcms-go/demo

ADD build build
CMD ["/usr/local/app/vcms-go/demo/build/ffmpegdemo"]
