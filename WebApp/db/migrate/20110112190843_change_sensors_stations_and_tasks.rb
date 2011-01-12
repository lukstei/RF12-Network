class ChangeSensorsStationsAndTasks < ActiveRecord::Migration
  def self.up
	remove_column :stations, :sensor
	remove_column :tasks, :sensor
	remove_column :sensors, :port
  end

  def self.down
	add_column :stations, :sensor, :string
	add_column :tasks, :sensor, :string
	add_column :sensors, :port , :integer 
  end
end
