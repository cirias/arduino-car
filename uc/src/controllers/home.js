export default {
  get(req, res) {
    return res.send(`Hello ${req.params.name}`);
  },
};
