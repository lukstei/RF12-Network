class AddIntervallToSensors < ActiveRecord::Migration
  def self.up
	add_column :sensors, :intervall, :integer 
  end

  def self.down
	remove_column :sensors, :intervall
  end
end
