import React from 'react';

export default class ControlBtn extends React.Component {
  handleTouchStart(event) {
    this.props.updateMotion(this.props.name);
    this.preventDefault();
  }
  handleTouchEnd(event) {
    if (this.props.motion === this.props.name) {
      this.props.stopMotion();
    }
    this.preventDefault();
  }
  render() {
    let className = `fa fa-play medium-text ${this.props.name}-btn${this.props.name===this.props.motion?'-big':''}`;

    return (
        <i className={className} onTouchStart={this.handleTouchStart.bind(this)} onTouchEnd={this.handleTouchEnd.bind(this)}></i>
    );
  }
}
