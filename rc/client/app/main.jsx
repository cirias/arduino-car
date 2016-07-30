require('../node_modules/font-awesome/css/font-awesome.css');
require('./style/main.css');

import React from 'react';
import ReactDOM from 'react-dom';
import Dashboard from './components/dashboard.jsx';

main();

function main() {
  ReactDOM.render((
    <Dashboard />
  ), document.getElementById('app'));
}
