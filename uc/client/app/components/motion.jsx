import React from 'react';
import $ from 'jquery';

export default class Motion extends React.Component {
  constructor() {
    super();
    this.state = {motion: 'stop'};
  }
  sendMotion() {
    $.ajax({
      url: `/api/motion/${this.state.motion}`,
      method: 'GET',
    }).done(
      ()=>console.log('send motion request success')
    ).fail(err=>console.log(`failt to send request: ${err}`));
  }
  handleMotionKeyDown(event) {
    switch (true) {
      case 37 === event.keyCode && this.state.motion !== 'left':
        console.log('left');
        this.setState({ motion: 'left' }, this.sendMotion);
        break;
      case 38 === event.keyCode && this.state.motion !== 'forward':
        console.log('forward');
        this.setState({ motion: 'forward' }, this.sendMotion);
        break;
      case 39 === event.keyCode && this.state.motion !== 'right':
        console.log('right');
        this.setState({ motion: 'right' }, this.sendMotion);
        break;
      case 40 === event.keyCode && this.state.motion !== 'backward':
        console.log('backward');
        this.setState({ motion: 'backward' }, this.sendMotion);
        break;
    }
  }
  handleMotionKeyUp(event) {
    if (event.keyCode >= 37 && event.keyCode <= 40) {
      console.log('stop');
      this.setState({ motion: 'stop' }, this.sendMotion);
    }
  }
  componentWillMount() {
    document.addEventListener("keydown", this.handleMotionKeyDown.bind(this), false);
    document.addEventListener("keyup", this.handleMotionKeyUp.bind(this), false);
  }
  render() {
    return <h1>{this.state.motion}</h1>;
  }
}
