# Config
Troubleshooting:
- An unexpected error occurred: [...] unable to get local issuer certificate

This error occurs when running under a proxy
```bash
yarn config set "strict-ssl" false #-g for global
```