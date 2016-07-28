import dgram from 'dgram';
import config from '../config.js';

const client = dgram.createSocket('udp4');

export default {
  get(req, res, next) {
    client.send(req.params.motion, config.remote.port, config.remote.host, err => {
      if (err) {
        return next(err);
      }

      console.log(`send ${req.params.motion}`);
      return res.send('ok');
    });
  },
};
