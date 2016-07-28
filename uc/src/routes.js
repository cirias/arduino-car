import home from './controllers/home.js';
import control from './controllers/control.js';

export default function (app) {
  app.get('/:name', home.get);
  app.get('/move/:motion', control.get);
}
