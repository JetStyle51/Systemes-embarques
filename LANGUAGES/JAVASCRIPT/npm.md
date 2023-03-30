# Introduction
The difference between npm and npx
https://www.freecodecamp.org/news/npm-vs-npx-whats-the-difference/

yarn is also a package manager but developed by Facebook
https://www.imaginarycloud.com/blog/npm-vs-yarn-which-is-better/

# help
- nmp fund

When you run npm fund it will list all the modules and packages you have installed that were created by companies or organizations that need money for their IT projects. You will see a list of webpages where you can send them money. So "funds" means "Angular packages you installed that could use some money from you as an option to help support their businesses".

- npm install [package-name]@[version-number]

- npm view [package-name]


- npm list [package-name]

to know the specific latest version of an installed package

- npm install [package-name]@[version-number]

to install an older version of a package

# Config
Add a proxy to npm

```bash
npm config set proxy http://username:password@host:port
npm config set https-proxy http://username:password@host:port
```

See the proxy configured for npm:
```bash
npm config list | grep proxy
```

See npm config
```bash
npm config list
```

Open create react-app specific browser:

https://www.tutorialfunda.com/reactjs/open-create-react-app-specific-browser/