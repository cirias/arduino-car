import React from 'react';
import ReactDOM from 'react-dom';
import Hello from './components/hello.jsx';
import Motion from './components/motion.jsx';

main();

function main() {
  ReactDOM.render((
    <div>
      <Hello />
      <Motion text="Motion"/>
    </div>
  ), document.getElementById('app'));
}
