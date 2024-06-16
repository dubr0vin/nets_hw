FROM fedora

RUN dnf install g++ iputils -y

WORKDIR /app

ADD find_mtu.cpp .

RUN g++ find_mtu.cpp -o find_mtu

ENTRYPOINT ["/app/find_mtu"]