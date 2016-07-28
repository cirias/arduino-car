import minimist from 'minimist';

const env = process.env.NODE_ENV || 'deployment';
const argv = minimist(process.argv.slice(2));

const config = {
  deployment: {
    remote: {
      host: argv.host,
      port: argv.port,
    },
    port: 8000,
  },
  production: {
    remote: {
      host: argv.host,
      port: argv.port,
    },
    port: 8000,
  },
};

export default config[env];
