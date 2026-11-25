# Development container for "Introduction to Programming with Modern C++".
# GCC 15 (needed for std::println("{}", vector)), CMake, Ninja, GDB, clang-format,
# raylib's system dependencies for chapters 13-14, and pandoc for building the EPUB.
FROM gcc:15

ARG PANDOC_VERSION=3.1.13
ARG USERNAME=dev
ARG USER_UID=1000
ARG USER_GID=1000

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        cmake ninja-build gdb clang-format git ca-certificates curl sudo \
        libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

# Debian's pandoc is too old for scripts/build-epub.sh (--split-level needs pandoc 3).
RUN arch="$(dpkg --print-architecture)" \
    && curl -fsSL -o /tmp/pandoc.deb \
        "https://github.com/jgm/pandoc/releases/download/${PANDOC_VERSION}/pandoc-${PANDOC_VERSION}-1-${arch}.deb" \
    && apt-get install -y /tmp/pandoc.deb \
    && rm /tmp/pandoc.deb

# A non-root user for working in the container.
RUN groupadd --gid "${USER_GID}" "${USERNAME}" \
    && useradd --uid "${USER_UID}" --gid "${USER_GID}" --create-home --shell /bin/bash "${USERNAME}" \
    && echo "${USERNAME} ALL=(root) NOPASSWD:ALL" > "/etc/sudoers.d/${USERNAME}" \
    && chmod 0440 "/etc/sudoers.d/${USERNAME}"

USER ${USERNAME}
WORKDIR /workspace
