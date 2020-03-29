FROM debian:stretch-slim
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
ENV LANG=zh_CN.UTF-8 \
    LANGUAGE=zh_CN:zh \
    LC_ALL=zh_CN.UTF-8
RUN mkdir -p /usr/local/app
WORKDIR /usr/local/app
ADD build build
CMD ["echo","todo"]
