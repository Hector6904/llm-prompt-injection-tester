FROM ubuntu:24.04 AS build
RUN apt-get update && apt-get install -y --no-install-recommends build-essential cmake ca-certificates && rm -rf /var/lib/apt/lists/*
WORKDIR /src
COPY CMakeLists.txt ./
COPY include ./include
COPY src ./src
COPY web ./web
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --target tester_web -j2

FROM ubuntu:24.04
RUN useradd -m app
WORKDIR /app
COPY --from=build /src/build/tester_web /app/tester_web
COPY --from=build /src/build/web /app/web
USER app
ENV HOST=0.0.0.0
ENV PORT=10000
EXPOSE 10000
CMD ["/app/tester_web"]
