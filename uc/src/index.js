import config from './config.js';

import express from 'express';
import bodyParser from 'body-parser';

import routes from './routes.js';

const app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

routes(app);

app.listen(config.port, () => {
  console.log('Listening on', config.port);
});
