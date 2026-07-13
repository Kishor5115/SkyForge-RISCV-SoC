# How To Install IIC-OSIC-TOOLS on Windows

> **Source:** Adapted from the [IEEE SSCS Chipathon 2026](https://www.chipathon.org/)
> documentation. Screenshots from the original guide are omitted here; see the upstream
> Chipathon docs for the annotated walkthrough with images.

This quick start guide explains how to get the IIC-OSIC-TOOLS up and running with Docker Desktop on Windows.

## Initial Notes

This installation assumes a reasonably modern and updated installation of Windows 10 or 11. This means WSL2 supports the WSLg graphical backend, which provides the required X-Server and Wayland interfaces to the container.

## Docker Desktop Install

A detailed explanation can be found on [Install Docker Desktop on Windows](https://docs.docker.com/desktop/setup/install/windows-install/).

1. Download Docker Desktop [here](https://desktop.docker.com/win/main/amd64/Docker%20Desktop%20Installer.exe?utm_source=docker&utm_medium=webreferral&utm_campaign=docs-driven-download-win-amd64) (Windows, x86_64; for different architectures, check the website).

2. Run the installer and enable "Use WSL2 instead of Hyper-V". Do not enable "Allow Windows Containers".

3. After the installation succeeds, press "Close and restart".

4. After the reboot, launch "Docker Desktop" from your Start menu or the desktop shortcut. Docker will ask you about the Subscription Service Agreement.

5. Docker will ask you to finish the setup. Select "Use recommended settings". This will require you to enter your administrator password at some point.

6. Docker starts up now. You can skip the login and the initial questionnaire. It takes a few moments for Docker to start the engine.

7. Docker is now started up and ready to use!

8. Start the IIC-OSIC-TOOLS container (see [`instructions/README.md`](../README.md) for the exact SkyForge launch command). If Windows Defender blocks a start script, click "More Information" and then "Run anyway".

9. On first run, Docker will pull the container image. This can take a while. **WARNING:** This process might use more than 20 GB of storage on your machine. Please make sure enough space is free on your hard drive.

10. Once the image is downloaded and unpacked, the container is running. For the VNC mode, open a browser at [http://localhost:80](http://localhost:80) (default password "abc123"). For the Jupyter mode, open [http://localhost:8888](http://localhost:8888).

> **NOTE:** After pulling the image, the memory usage of the Docker Engine can be quite high. In the bottom-left of the Docker Desktop app, click the three dots → "Restart Docker" to free memory.

## Tips and Tricks

### Store Files Persistently
The container shares files between the host and the container. On the host, this directory is in your user directory under `eda\designs` (usually `C:\Users\<username>\eda\designs`). In the container, it is at `/foss/designs`.
**IMPORTANT:** This is the only directory that is persistent through a container update! Any other files in the container are deleted when the container is deleted or updated.

### Does my container even run?
If your container does not open a terminal, open the Docker Desktop application and click on "Containers" to see whether your container exists and is running. This page can also be used to stop, restart, and delete the container.

### How to Update the Container
1. Go to the Docker Desktop app and stop and delete the container.
2. Go to "Images" and pull the new version (three dots → "Pull").
3. Run the start command / start-script again.
