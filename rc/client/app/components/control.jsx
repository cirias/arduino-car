import React from 'react';
import CtlBtn from './control-button.jsx'

export default class Control extends React.Component {
  render() {
    return (
      <div className="control">
        <div>
          <CtlBtn {...this.props} name="forward" />
        </div>
        <div>
          <CtlBtn {...this.props} name="left" />
          <CtlBtn {...this.props} name="right" />
        </div>
        <div>
          <CtlBtn {...this.props} name="backward" />
        </div>
      </div>
    );
  }
}
