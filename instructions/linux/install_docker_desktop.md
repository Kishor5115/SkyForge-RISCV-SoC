# How To Install IIC-OSIC-TOOLS on Linux

> **Source:** Adapted from the [IEEE SSCS Chipathon 2026](https://www.chipathon.org/)
> documentation. Screenshots from the original guide are omitted here; see the upstream
> Chipathon docs for the annotated walkthrough with images.

This quick start guide explains how to get the IIC-OSIC-TOOLS up and running with Docker Desktop on Linux.

## Initial Notes

This installation shows how the installation works with Docker Desktop on Ubuntu 25.04. Docker Desktop is the easy way to manage Docker Containers, since it also provides a GUI. If you are familiar with Docker (or you are good with the terminal), we recommend you use the classic Docker CE without a GUI, since it has better performance. But, to say it again: the safe route is Docker Desktop!

## Docker Desktop Install

A detailed explanation can be found on [Install Docker Desktop on Linux](https://docs.docker.com/desktop/setup/install/linux/). Follow this installation tutorial, especially when you are not on Ubuntu!

1. Check if your system has KVM (the Kernel Virtual Machine, required to run Docker Desktop) enabled. Do this by running
`sudo apt install cpu-checker` and then running `kvm-ok`. If it outputs that "KVM acceleration can be used" you are fine.
Additionally, you have to add your user to the KVM group so you can run virtual machines: `sudo usermod -aG kvm $USER`.

2. Enable the Docker Repository in Ubuntu, run the following script in the terminal:
```bash
# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc

# Add the repository to Apt sources:
echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "${UBUNTU_CODENAME:-$VERSION_CODENAME}") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
```

3. Download Docker Desktop [here](https://desktop.docker.com/linux/main/amd64/docker-desktop-amd64.deb?utm_source=docker&utm_medium=webreferral&utm_campaign=docs-driven-download-linux-amd64) (Ubuntu, x86_64; for different architectures, check the website).

4. Double-click the `.deb` file and install it using Software Center. Since the repository is already enabled, all required dependencies are pulled in automatically.

5. Launch "Docker Desktop" from your Start menu or the desktop shortcut. Docker will ask you about the Subscription Service Agreement.

6. Docker starts up now. You can skip the login and the initial questionnaire. It takes a few moments for Docker to start the engine.

7. Docker is now started up and ready to use!

8. If you are planning on using the X/Wayland mode, you have to install "socat", which provides the interface between the container and the host's graphical environment. Do this by running `sudo apt install -y socat`.

9. Start the IIC-OSIC-TOOLS container (see [`instructions/README.md`](../README.md) for the exact SkyForge launch command). Docker will pull the container image on first run. **WARNING:** This process might use more than 20 GB of storage on your machine. Please make sure enough space is free on your hard drive.

10. Once the image is downloaded and unpacked, the container is running. For the VNC mode, open a browser at [http://localhost:80](http://localhost:80) (default password "abc123"). For the Jupyter mode, open [http://localhost:8888](http://localhost:8888).

## Tips and Tricks

### Store Files Persistently
The container shares files between the host and the container. On the host, this directory is in your user directory under `eda/designs` (usually `/home/<username>/eda/designs`). In the container, it is at `/foss/designs`.
**IMPORTANT:** This is the only directory that is persistent through a container update! Any other files in the container are deleted when the container is deleted or updated.

### Does my container even run?
If your container does not open a terminal, open the Docker Desktop application and click on "Containers" to see whether your container exists and is running. This page can also be used to stop, restart, and delete the container.

### How to Update the Container
1. Go to the Docker Desktop app and stop and delete the container.
2. Go to "Images" and pull the new version (three dots → "Pull").
3. Run the start command / start-script again.
