const form = document.querySelector('#todo-form');
const todo = document.querySelector('#todo-input');

form.addEventListener('submit', function(e) {
  e.preventDefault();
  todo.value = '';
});
