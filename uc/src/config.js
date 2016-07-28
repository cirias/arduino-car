const env = process.env.NODE_ENV || 'deployment';

const config = {
  deployment: {
    remote: {
      host: '',
      port: 0,
    },
    port: 8000,
  },
  production: {
    remote: {
      host: '',
      port: 0,
    },
    port: 8000,
  },
};

export default config[env];
