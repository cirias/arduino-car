var config = {
  entry: [
    './app/main.jsx'
  ],
  output: {
      path: './build',
      filename: 'bundle.js',
  },
  module: {
    loaders: [{
      test: /\.jsx?$/, // A regexp to test the require path. accepts either js or jsx
      loader: 'babel', // The module to load. "babel" is short for "babel-loader"
      query: {
	      presets:['es2015','react']
      }
    }, {
      test: /\.css$/,
      loader: 'style!css'
    }, {
      test: /\.(png|jpg)$/,
      loader: 'url?limit=25000'
    }],
  }
};

module.exports = config;
