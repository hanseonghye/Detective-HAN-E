$(document).ready(function() {
	$('#upload_btn').onclick(function() {
		var form_date=new FormData($('#upload-form')[0]);
		$.ajax({
			type: 'POST',
			url : '/upload',
			data: form_data,
			success: function(data){
				console.log('ss')
			},
		});
	});
});