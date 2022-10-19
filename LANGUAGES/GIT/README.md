# GIT
# Introduction
GIT is a tool to manage code versions

# Commands
Check your git **version**
```bash
$ git --version
$ git -v
```
## Configuration
### Username
Set your user name
```bash
$ git config --global user.name "your name"

$ git config --global user.email “yourname@gmail.com”
```

### Proxy
Set the proxy if needed
```bash
$ git config --global http.proxy force-proxy-eur.pac.schneider-electric.com:443

$ git config --global https.proxy force-proxy-eur.pac.schneider-electric.com:443
```
### Git Hooks
https://git-scm.com/docs/githooks
```bash
$ git config --global core.hooksPath .githooks
```
Check that the core.autocrlf is set to true whether you work on cross platform project.
```bash
$ git config -l | grep autocrlf 
```

## LFS
https://git-lfs.github.com/

An open source Git extension for versioning large files.
Git Large File Storage (LFS) replaces large files such as audio samples, videos, datasets, and graphics with text pointers inside Git, while storing the file contents on a remote server like GitHub.com or GitHub Enterprise.

```bash
$ git lfs install
```
```bash
$ git lfs track "*.psd"
```
```bash
$ git add .gitattributes
```

> Note that defining the file types Git LFS should track will not, by itself, convert any pre-existing files to Git LFS, such as files on other branches or in your prior commit history. To do that, use the ![git lfs migrate(1)](https://github.com/git-lfs/git-lfs/blob/main/docs/man/git-lfs-migrate.adoc?utm_source=gitlfs_site&utm_medium=doc_man_migrate_link&utm_campaign=gitlfs) command, which has a range of options designed to suit various potential use cases.

