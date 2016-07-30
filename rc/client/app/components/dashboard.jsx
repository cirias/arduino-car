import $ from 'jquery';
import React from 'react';
import Hello from './hello.jsx';
import Motion from './motion.jsx';
import Control from './control.jsx';

export default class Dashboard extends React.Component {
  constructor() {
    super();
    this.state = {motion: 'stop'};
  }
  setMotion(motion) {
    if (this.state.motion === motion) {
      return;
    }

    console.log(motion);
    this.setState({ motion });

    $.ajax({
      url: `/api/motion/${motion}`,
      method: 'GET',
    }).done(
      ()=>console.log('send motion request success')
    ).fail(err=>console.log(`failt to send request: ${err}`));
  }
  handleUpdateMotion(motion) {
    this.setMotion(motion);
  }
  handleStopMotion() {
    this.setMotion('stop');
  }
  handleMotionKeyDown(event) {
    if (event.keyCode > 40 || event.keyCode < 37) {
      return;
    }

    event.preventDefault();
    event.stopPropagation();
    switch (true) {
      case 37 === event.keyCode:
        this.setMotion('left');
        break;
      case 38 === event.keyCode:
        this.setMotion('forward');
        break;
      case 39 === event.keyCode:
        this.setMotion('right');
        break;
      case 40 === event.keyCode:
        this.setMotion('backward');
        break;
    }
  }
  handleMotionKeyUp(event) {
    if (event.keyCode >= 37 && event.keyCode <= 40) {
      this.handleStopMotion();
    }
  }
  componentWillMount() {
    document.addEventListener("keydown", this.handleMotionKeyDown.bind(this), false);
    document.addEventListener("keyup", this.handleMotionKeyUp.bind(this), false);
  }
  render() {
    return (
      <div className="dashboard">
        <Motion motion={this.state.motion} />
        <Control motion={this.state.motion} updateMotion={this.handleUpdateMotion.bind(this)} stopMotion={this.handleStopMotion.bind(this)} />
      </div>
    );
  }
}
