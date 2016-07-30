import React from 'react';

export default class Motion extends React.Component {
  constructor() {
    super();
  }
  render() {
    let icon;
    switch (this.props.motion) {
      case 'forward':
        icon = <i className="fa fa-arrow-up large-text forward"></i>;
        break;
      case 'backward':
        icon = <i className="fa fa-arrow-down large-text backward"></i>;
        break;
      case 'left':
        icon = <i className="fa fa-undo large-text left"></i>;
        break;
      case 'right':
        icon = <i className="fa fa-repeat large-text right"></i>;
        break;
      case 'stop':
        icon = <i className="fa fa-stop large-text"></i>;
        break;
    }

    return (
      <div className="motion">
        { icon }
      </div>
    );
  }
}
