import control from './controllers/control.js';

export default function (app) {
  app.get('/api/motion/:motion', control.get);
}
